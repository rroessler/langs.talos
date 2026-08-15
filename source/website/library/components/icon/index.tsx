/// Vendor Modules
import { DynamicIcon, IconName } from 'lucide-react/dynamic';
import { Icon as Wrap, IconNode, LucideProps } from 'lucide-react';

/** Icon Details. */
export type Icon = Icon.Name | Icon.Props | Icon.Node;
export namespace Icon {
    //  TYPEDEFS  //

    /** Potentially dyanmic icon name. */
    export type Name = IconName;

    /** Icon Node Typing. */
    export type Node = IconNode;

    /** Dynamic Icon Properties. */
    export type Props = LucideProps & { readonly name: Name };

    //  PUBLIC METHODS  //

    /**
     * Constructs dynamic icons.
     * @param input                 Properties to bind.
     */
    export function Dynamic(input?: Name, props?: Omit<Props, 'name'>): React.ReactNode;
    export function Dynamic(node: Node, props?: Omit<Props, 'name'>): React.ReactNode;
    export function Dynamic(props: Props): React.ReactNode;
    export function Dynamic(input?: Icon, props?: Omit<Props, 'name'>): React.ReactNode {
        if (typeof input === 'undefined') return null; // ignore invalid inputs now
        props = Object.assign({ size: 16 } satisfies Omit<Props, 'name'>, props ?? {});
        if (typeof input === 'string') return Dynamic({ name: input, ...props });
        if (Array.isArray(input)) return <Wrap iconNode={input} {...props} />;
        return <DynamicIcon {...input} />; // otherwise is a valid icon
    }
}
