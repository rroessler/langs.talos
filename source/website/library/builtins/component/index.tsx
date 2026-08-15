/// Vendor Modules
import { Heading } from 'fumadocs-ui/components/heading';

/// Website Modules
import { Fragment } from '@/website/components';

/// Package Modules
import { Property } from '../property';
import { Registry } from '../registry';
import { Ancillary } from '../descriptor';

/** Builtins Documentation Component. */
export interface Component extends Component.Props {}
export function Component({ name, ancillary, children }: Component) {
    // attempt resolving the required component
    const builtin = Registry.resolve(name, ancillary);
    if (typeof builtin === 'undefined') return;

    // and return the resulting documentation
    return (
        <Fragment>
            <Heading as="h2" id="overview" children="Overview" />
            {children /* all the children come from website side */}

            <Component.Section id="fields" heading="Fields" items={builtin.fields} />
            <Component.Section id="statics" heading="Statics" items={builtin.statics} />
        </Fragment>
    );
}

export namespace Component {
    //  TYPEDEFS  //

    /** Documentation Component Properties. */
    export type Props = React.PropsWithChildren<{
        readonly name: string;
        readonly ancillary?: Ancillary;
    }>;

    /** Documentation Component Section. */
    export type Section = { id: string; heading: string; items?: Property[] };
    export function Section({ id, heading, items }: Section) {
        // ignore if the incoming items are invalid
        if (!items?.length) return;

        // prepare all the properties to be used
        const properties = items.map((item) => <Property key={item.name} parent={id.toLowerCase()} {...item} />);

        // otherwise resolve as normal
        return (
            <Fragment>
                <Heading as="h2" id={id} className="mt-5" children={heading} />
                {properties}
            </Fragment>
        );
    }
}
