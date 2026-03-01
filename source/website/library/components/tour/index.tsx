/// Node Modules
import * as fs from 'node:fs';

/// Website Modules
import { Assets } from '@/website/assets';
import { Anchor } from '../anchor';

/** Language Tour Components. */
export namespace Tour {
    //  PUBLIC METHODS  //

    /** Step Component. */
    export interface Step {
        readonly index: number;
        readonly href: string;
        readonly title: string;
    }

    /** Table of Contents Component. */
    export interface Contents {}
    export function Contents() {
        // prepare the output steps to be used
        const steps: Step[] = [];

        // attempt destructing all the necessary steps
        for (const item of fs.readdirSync(Assets.tour())) {
            // trim the trailing details
            const leading = item.replaceAll(/\.mdx?$/g, '');

            // attempt pulling the rest of the details out
            const [base, ...segments] = leading.split('-');

            // pull out the step number now
            const index = Number.parseInt(base);
            if (Number.isNaN(index)) continue;

            // construct the necessary href now as well
            const href = `/docs/tour/${leading}`;

            // construct the title to be used
            const title = segments.map((part) => part[0].toUpperCase() + part.slice(1)).join(', ');

            // construct the resulting step now
            steps.push({ title, index, href });
        }

        // prepare the list items now
        const list = steps
            .sort((a, b) => a.index - b.index)
            .map((step) => <li key={step.index} children={<Anchor href={step.href} children={step.title} />} />);

        // and show the resulting contents now
        return <ol children={list} />;
    }
}
